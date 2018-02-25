import glob

class Reader():
    def __init__(self):
        self.fileName = '' #file name
        self.highBit = 'X' #define what is a high bit on the file
        self.letter = []   #define the list which will store the final letter
    
    def getFilename(self):
        """
        This function gets the name of the inputfile letters*.txt
        """
        names = glob.glob('letters*.txt')
        if len(names) >= 1:
            self.fileName = names[0]
            print('filename = ' + self.fileName)
            print("")
        else:
            self.fileName = 'File not found (letters*.txt)'

    def readFile(self):
        
        """
        This function reads the file =D
        """
        self.getFilename()
        with open(self.fileName, 'r') as pfile: # open inputfile
            self.file = pfile.readlines()

        fakeFile = []

        for line in self.file:
            if line[0] == "#":
                fakeFile.append(line)

        self.file = fakeFile

    def getData(self):
        """
        This function extract the data from the file
        inputfile =DD
        """
        self.bufferBit = []

        for i in (range(len(self.file))):
            start=self.file[i].find("#")
            end=self.file[i][start+1:].find('#')
            bufferBit = []
            self.bufferBit.append([])

            for j in range(end-start):
                if self.file[i][j+start+1] == self.highBit:
                    bufferBit.append('X')
                    self.bufferBit[i].append("1")
                else:
                    bufferBit.append(' ')
                    self.bufferBit[i].append("0")
            print(bufferBit)
        print("")
        
    def prepareLetter(self):
        """
        This function prepares the letter
        """
        byte = ''

        for j in range(len(self.bufferBit[0])):
            byte = ''
            for i in range(len(self.bufferBit)):
                byte = byte + self.bufferBit[i][j]
            byte = byte[::-1] #reverse the string to fit the expected format

            self.letter.append(byte)

    def writeLetter(self):
        """
        This function writes the letter in the original file (at its end)
        """
        letter = '{'
        for item in self.letter:
            letter = letter + "B" + item + ", "

        letter = letter[:-2] + "}, //"
        print(letter)
        
        with open(self.fileName, 'w') as pfile:
            for line in self.file:
                pfile.write(line)
            pfile.write("\r\n\r\n"+letter)


reader = Reader()
reader.readFile()
reader.getData()
reader.prepareLetter()
reader.writeLetter()