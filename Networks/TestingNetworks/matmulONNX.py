import os
import torch
import torch.nn as nn
import numpy as np
import onnx
from onnxruntime.quantization import quantize_static, CalibrationDataReader, QuantFormat, QuantType

from onnx import helper, numpy_helper, TensorProto, shape_inference

# Paths
size = 16
export_dir = "TestingNetworks/output/models/onnx"
os.makedirs(export_dir, exist_ok=True)
fp32_model_path = os.path.join(export_dir, f"matmulModel_{size}_fp32.onnx")
quant_model_path = os.path.join(export_dir, f"matmulModel_{size}_int8_qdq.onnx")
final_model_path = os.path.join(export_dir, f"matmulModel_{size}_int8_pure.onnx")

# Define Model
class MatMulModel(nn.Module):
    def __init__(self, W):
        super().__init__()
        self.weight = nn.Parameter(W, requires_grad=False)
    def forward(self, x):
        return torch.matmul(x, self.weight.t())

# Create & Export FP32 ONNX model
W = torch.rand((size, size), dtype=torch.float32)
model = MatMulModel(W).eval()
dummy_input = torch.zeros(1, size)

torch.onnx.export(
    model, dummy_input, fp32_model_path,
    input_names=["input"], output_names=["output"],
    dynamic_axes={"input": {0: "batch_size"}, "output": {0: "batch_size"}},
    opset_version=13,
)

# Calibration Reader
class CalibrationReader(CalibrationDataReader):
    def __init__(self, size):
        self.data = iter([{"input": np.random.uniform(-1, 1, (1, size)).astype(np.float32)} for _ in range(100)])
    def get_next(self):
        return next(self.data, None)

calibration_reader = CalibrationReader(size)

# Static Quantization
quantize_static(
    model_input=fp32_model_path,
    model_output=quant_model_path,
    calibration_data_reader=calibration_reader,
    quant_format=QuantFormat.QDQ,
    activation_type=QuantType.QInt8,
    weight_type=QuantType.QInt8,
    per_channel=True,
    reduce_range=False,
)

# ✅ Post-process: Strip Q/DQ nodes and set true int8 I/O
model = onnx.load(quant_model_path)

# Remove QuantizeLinear and DequantizeLinear nodes
nodes = []
for node in model.graph.node:
    if node.op_type not in ['QuantizeLinear', 'DequantizeLinear']:
        nodes.append(node)
model.graph.ClearField("node")
model.graph.node.extend(nodes)

# Force input/output to int8
for input_tensor in model.graph.input:
    input_tensor.type.tensor_type.elem_type = TensorProto.INT8
for output_tensor in model.graph.output:
    output_tensor.type.tensor_type.elem_type = TensorProto.INT8

# (Optional) Shape inference
model = shape_inference.infer_shapes(model)

# Save final model
onnx.save(model, final_model_path)
print(f"✅ Final fully INT8 model saved to: {final_model_path}")
