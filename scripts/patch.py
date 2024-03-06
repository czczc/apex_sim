import shutil, sys

lines = []

def comment_line(i):
    lines[i] = '// ' + lines[i]

def remove_checkoverlap(i):
    # find the last ')''s line and replace 'true' to 'false'
    stack =[]
    while True:
        line = lines[i]
        if ('// fWorldLength/2.-1*fDetectorLength/2.),' in line): 
            # print('!!!!!', line)
            i += 1
            continue
        for c in line:
            if (c=='('): stack.append(c)
            elif (c == ')'): stack.pop()
        
        if (len(stack)==0): 
            # print(line.replace('true)', 'false)'))
            lines[i] = line.replace('true)', 'false)')
            break
        else:
            # print('not here:', line)
            i += 1


def patch_hh():
    """
    patch the .hh file 
    """
    global lines
    lines = open('../include/DetectorConstruction.hh').readlines()
    outfile = './DetectorConstruction.hh'
    with open(outfile, 'w') as fout:
        for i in range(len(lines)):
            if 'private:' in lines[i]:
                comment_line(i)
            
            fout.write(lines[i])


def patch_cc():
    """
    patch the .cc file 
    """
    global lines
    lines = open('../src/DetectorConstruction.cc').readlines()
    outfile = './DetectorConstruction.cc'
    with open(outfile, 'w') as fout:
        for i in range(len(lines)):
            if 'G4PVPlacement(' in lines[i]:
                remove_checkoverlap(i)
            if 'cout' in lines[i] and 'endl' in lines[i]:
                comment_line(i)
            
            fout.write(lines[i])

def move():
    shutil.move('../include/DetectorConstruction.hh', './DetectorConstruction.hh.old')
    shutil.move('../src/DetectorConstruction.cc', './DetectorConstruction.cc.old')
    shutil.move('./DetectorConstruction.hh', '../include/DetectorConstruction.hh')
    shutil.move('./DetectorConstruction.cc', '../src/DetectorConstruction.cc')

def restore():
    shutil.move('../include/DetectorConstruction.hh', './DetectorConstruction.hh')
    shutil.move('../src/DetectorConstruction.cc', './DetectorConstruction.cc')
    shutil.move('./DetectorConstruction.hh.old', '../include/DetectorConstruction.hh')
    shutil.move('./DetectorConstruction.cc.old', '../src/DetectorConstruction.cc')


if __name__ == '__main__':
    # print(sys.argv)
    patch_hh()
    patch_cc()
    if (len(sys.argv)==1):
        print('''usage: python3 patch.py [option]
            m: move
            t: test
            r: restore
              ''')
    else:
        option = sys.argv[1]
        if (option == 'm'):
            move()
        elif (option == 'r'):
            restore()
    
