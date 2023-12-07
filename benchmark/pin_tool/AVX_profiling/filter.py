#!/bin/python3

# Define a function to filter unique instructions
def filter_unique_instructions(filename):
    unique_instructions = set()

    # Open the trace file
    with open(filename, 'r') as file:
        # Read each line in the file
        for line in file:
            # Split the line and extract the instruction
            parts = line.split()
            if len(parts) > 1:
                instruction = parts[1]
                # Add the instruction to our set
                unique_instructions.add(instruction)

    # Print out the unique instructions
    print("Unique Instructions:")
    for instruction in unique_instructions:
        print(instruction)

# Call the function with your trace file's name
filter_unique_instructions('SIMD.trace')

