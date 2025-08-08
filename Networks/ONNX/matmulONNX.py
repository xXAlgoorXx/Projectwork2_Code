import onnx
from onnx import helper, TensorProto

# INT8 input tensors (no change)
input_A = helper.make_tensor_value_info('A', TensorProto.INT8, [1, 10])
input_B = helper.make_tensor_value_info('B', TensorProto.INT8, [10, 10])
output_Y = helper.make_tensor_value_info('Y', TensorProto.INT8, [1, 10])

# Initializers for scale and zero points
init_tensors = [
    helper.make_tensor('A_scale', TensorProto.FLOAT, [1], [0.1]),
    helper.make_tensor('A_zero_point', TensorProto.INT8, [1], [0]),
    helper.make_tensor('B_scale', TensorProto.FLOAT, [1], [0.2]),
    helper.make_tensor('B_zero_point', TensorProto.INT8, [1], [0]),
    helper.make_tensor('Y_scale', TensorProto.FLOAT, [1], [0.3]),
    helper.make_tensor('Y_zero_point', TensorProto.INT8, [1], [0])
]

# Node
qlinear_matmul_node = helper.make_node(
    'QLinearMatMul',
    inputs=[
        'A', 'A_scale', 'A_zero_point',
        'B', 'B_scale', 'B_zero_point',
        'Y_scale', 'Y_zero_point'
    ],
    outputs=['Y']
)

# Graph
graph_def = helper.make_graph(
    nodes=[qlinear_matmul_node],
    name='QLinearMatMulGraph',
    inputs=[input_A, input_B],  # Only A and B are inputs now
    outputs=[output_Y],
    initializer=init_tensors
)

# Model
model_def = helper.make_model(graph_def, producer_name='onnx-qlinear-matmul')
model_def.ir_version = 9
model_def.opset_import[0].version = 10

# Save
onnx.checker.check_model(model_def)
onnx.save(model_def, 'ONNX/qlinear_matmul.onnx')
