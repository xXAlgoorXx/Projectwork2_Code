import torch
import torch.nn as nn
import onnx
class Int8MatVec(nn.Module):
    def __init__(self, size):
        super().__init__()
        self.weight = torch.nn.Parameter(torch.randint(-128, 127, (size, size), dtype=torch.int8).float())

    def forward(self, x):
        return torch.matmul(x, self.weight.t())

def export_int8_input_model(size):
    model = Int8MatVec(size)
    model.eval()

    # Force input tensor to int8
    dummy_input = torch.randint(-128, 127, (1, size), dtype=torch.int8).float()

    torch.onnx.export(
        model, dummy_input,
        f"ONNX/output/matvec_trueint8_{size}.onnx",
        input_names=["input"],
        output_names=["output"],
        opset_version=13,
        dynamic_axes=None
    )

    # Patch input type to INT8
    model_path = f"ONNX/output/matvec_trueint8_{size}.onnx"
    onnx_model = onnx.load(model_path)
    onnx_model.graph.input[0].type.tensor_type.elem_type = onnx.TensorProto.INT8
    onnx.save(onnx_model, model_path)
    print(f"✅ Exported true INT8 ONNX: {model_path}")

export_int8_input_model(16)
