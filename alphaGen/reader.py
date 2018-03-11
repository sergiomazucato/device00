import glob, cv2
import numpy as np

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
        
        # with open(self.fileName, 'w') as pfile:
        with open(self.fileName, 'a') as pfile:
            pfile.write("\r\n"+letter)
            # for line in self.file:
            #     pfile.write(line)
            # pfile.write("\r\n\r\n"+letter)

class LedMatrix(object):

    def __init__(self):
        """ inicialize context, more to come
        """
        self.ledsCols = 5  #number of columns
        self.ledsRows = 8  #number of rows
        self.spacing = 0.2 #spacing = 20% of led size
        self.height = 450  #height of the image
        self.ledCollor = (0,0,255) #red
        self.ledStroke = (0,0,0)   #black

        # self.ledSize = int(round(0.5*(self.height-10)/(self.ledsRows + (self.ledsRows+1)*self.spacing)))
        self.ledSize = int(round(0.5*(self.height-10)/(self.ledsRows+(self.ledsRows+1)*self.spacing)))
        self.length =  int(round(self.ledSize*2*(self.ledsCols+(self.ledsCols+1)*self.spacing)+10))

        self.matrix = np.full((self.height, self.length, 3), 255, dtype=np.uint8)
        self.draw_matrix()

    def draw_matrix(self):
        start = (5,5)
        vert = self.height-start[0]
        hor = self.length-start[1]
        end = (hor, vert)
        
        self.ledImage = cv2.rectangle(self.matrix, start, end, 0, 1)
        # startRow = int(round(0.5*(self.height-(2*self.ledSize*(self.ledsRows+(self.ledsRows+1)*self.spacing)-10)))+self.ledSize)

        startRow = int(round(5+self.ledSize+self.ledSize*2*self.spacing))
        startCol = int(round(5+self.ledSize+self.ledSize*2*self.spacing))

        lineY = int(startCol+self.ledSize+self.ledSize*self.spacing)
        # cv2.line(self.ledImage, (5, lineY), (self.length-5, lineY), self.ledStroke, 1)
        self.dot_line(5,self.length-5, lineY)

        lineY = int(startCol+5*(self.ledSize+self.ledSize*self.spacing))
        self.dot_line(5,self.length-5, lineY)
        # cv2.line(self.ledImage, (5, lineY), (self.length-5, lineY), self.ledStroke, 1)

        for ledRow in range(self.ledsRows):
            startCol = int(round(5+self.ledSize+self.ledSize*2*self.spacing))
            
            for ledCol in range(self.ledsCols):
                cv2.circle(self.ledImage,(startCol, startRow), self.ledSize, self.ledStroke, 1)
                startCol = startCol+int(round(5+self.ledSize*2+self.ledSize*self.spacing))
            
            startRow = startRow+int(round(5+self.ledSize*2+self.ledSize*self.spacing))

    def dot_line(self, start, end, yPos):
        spacing = int((end-start)/100)

        i = start
        while i<end:
            cv2.line(self.ledImage, (i, yPos), (i+1, yPos), self.ledStroke, 1)
            i=i+4

    def fill_highs(self, binary, column):
        startCol = int(round(5+self.ledSize+self.ledSize*2*self.spacing))
        startCol = startCol + column*int(round(5+self.ledSize*2+self.ledSize*self.spacing))

        startRow = int(round(5+self.ledSize+self.ledSize*2*self.spacing))

        for i in binary:
            if i == "1":
                cv2.circle(self.ledImage,(startCol, startRow), self.ledSize, self.ledCollor, -1)
                cv2.circle(self.ledImage,(startCol, startRow), self.ledSize, self.ledStroke, 1)
            startRow = startRow+int(round(5+self.ledSize*2+self.ledSize*self.spacing))

    def fill_matrix(self, binary):
        column = 0
        for col in binary:
            self.fill_highs(col[::-1], column)
            column = column + 1

    def print_matrix(self):
        cv2.imshow('ledMatrix', self.ledImage)
        cv2.waitKey(0)
        cv2.destroyAllWindows()

    def save_img(self, path):
         cv2.imwrite(path, self.ledImage)
        
reader = Reader()
ledMatrix = LedMatrix()

reader.readFile()
reader.getData()
reader.prepareLetter()
reader.writeLetter()

ledMatrix.fill_matrix(reader.letter)
ledMatrix.save_img("img.jpg")
# ledMatrix.print_matrix()

