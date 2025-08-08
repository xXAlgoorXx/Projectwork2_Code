import torch
import torch.nn as nn
import torch.onnx
import onnx
from onnxruntime.quantization import quantize_dynamic, QuantType

# Step 1: Define a simple 1-layer model
class SimpleNN(nn.Module):
    def __init__(self):
        super(SimpleNN, self).__init__()
        self.fc = nn.Linear(10, 5)  # Input: 10-dim, Output: 5-dim

    def forward(self, x):
        return self.fc(x)

model = SimpleNN()
model.eval()

# Step 2: Export to ONNX
dummy_input = torch.randn(1, 10)
onnx_model_path = "simple_model.onnx"

torch.onnx.export(
    model, 
    dummy_input, 
    onnx_model_path, 
    input_names=["input"], 
    output_names=["output"], 
    opset_version=13
)

print(f"Exported model to {onnx_model_path}")

# Step 3: Quantize the ONNX model to 8-bit
quantized_model_path = "simple_model_quant.onnx"
quantize_dynamic(
    model_input=onnx_model_path,
    model_output=quantized_model_path,
    weight_type=QuantType.QInt8  # 8-bit quantization
)

print(f"Quantized model saved to {quantized_model_path}")
