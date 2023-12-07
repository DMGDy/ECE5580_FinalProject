instructions = [];


with open("vec_ins.txt",'r') as file:
    for line in file:
        split_line = line.strip().split(',');
        if(split_line != ''):
            instructions.append(split_line[0]);

print(instructions);
