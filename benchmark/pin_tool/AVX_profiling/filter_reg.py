#!/bin/python3

def filter_unique_registers(filename):
    unique_registers = set()

    # Open the trace file
    with open(filename, 'r') as file:
        # Read each line in the file
        for line in file:
            # Split the line into parts
            parts = line.split()
            # Check if the line has more than the instruction mnemonic
            if len(parts) > 2:
                # Extract register names (excluding the instruction and address)
                registers = parts[2:]
                # Add each register to our set
                for reg in registers:
                    unique_registers.add(reg)

    # Print out the unique register names
    print("Unique Register Names:")
    for reg in unique_registers:
        print(reg)

# Call the function with your trace file's name
filter_unique_registers('SIMD.trace')

