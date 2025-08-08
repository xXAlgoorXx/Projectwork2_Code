import torch
import torch.nn as nn
import numpy as np

class Int8MatVec(nn.Module):
    def __init__(self, size):
        super().__init__()
        # Simulate int8 weights by constraining float values to int8 range
        self.weight = nn.Parameter(torch.randint(-128, 127, (size, size), dtype=torch.int8).float())

    def forward(self, x):
        # Input is float, but should contain int8-like values
        return torch.matmul(x, self.weight.t())

def export_matvec_model(size, filename):
    model = Int8MatVec(size)
    model.eval()

    # Dummy input: 1 batch x vector size
    dummy_input = torch.randint(-128, 127, (1, size), dtype=torch.int8).float()

    # Export ONNX
    torch.onnx.export(
        model,
        dummy_input,
        filename,
        input_names=["input"],
        output_names=["output"],
        dynamic_axes=None,
        opset_version=13
    )

    print(f"Exported clean matvec model of size {size} to: {filename}")

# Example: generate models for sizes 16, 32, 64...
sizes = [16, 32, 64, 128, 256, 512, 1024]
for s in sizes:
    export_matvec_model(s, f"ONNX/output/matvec_int8_{s}.onnx")
