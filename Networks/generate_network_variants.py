import os

# Configuration
base_file = "network.c"  # Path to your original network.c file (size 16)
target_sizes = [16, 32, 64, 128, 256, 512, 1024]
output_template = "network_{}.c"

def replace_symbols(content, size):
    # Rename Default suffix to SizeXX
    content = content.replace("_Default", f"_Size{size}")
    content = content.replace("NN_Instance_Default", f"NN_Instance_Size{size}")
    return content

def generate_variant(size):
    with open(base_file, "r") as f:
        content = f.read()
    
    updated_content = replace_symbols(content, size)
    output_file = output_template.format(size)

    with open(output_file, "w") as f:
        f.write(updated_content)
    
    print(f"[✓] Generated: {output_file}")

if __name__ == "__main__":
    if not os.path.exists(base_file):
        print(f"[!] Base file '{base_file}' not found.")
        exit(1)

    for size in target_sizes:
        generate_variant(size)
