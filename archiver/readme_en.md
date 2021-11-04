Archiver
In this task, you have to implement the archiver through Huffman's algorithm.
The archiver must have the following CLI:

archiver -c archive_name file1 [file2 ...] - back up fil1, file2, ... and save the result to a archive_name file.

archiver -d archive_name - unzip files from archive_name archive and put them in the current directory. File names must be preserved during backup and unzip.

archiver -h - displays help for using the program.

Algorithm
The compression algorithm is structured as follows:

The frequency of 8-bit characters in the file is calculated. In addition to the file contents, you need to consider the frequencies of characters in the file name, as well as add three service symbols FILENAME_END=256, ONE_MORE_FILE=257, ARCHIVE_END=258 with frequencies 1. The purpose of these characters will be described later. Thus, 9 bits are needed to encode the extended alphabet.
The binary encoding is built using the following procedure:

For each alphabetic character, the corresponding vertex is added to the priority queue. The ordering of the vertices in the queue is carried out according to the non-decreasing frequencies of characters in the file (in the "beginning" of the queue there is always the vertex with the symbol with the lowest occurrence in the file).
As long as there is more than one element in the queue, two minimum priority vertices A and B are retrieved from the queue. A new vertex C is created, the children of which are vertices A and B.
Vertex C is queued with a priority equal to the sum of the priorities of vertices A and B.
At the end of the procedure, exactly one peak remains in the queue, which is the root of the built boron. Leaf nodes are terminal nodes.
Each terminal vertex has a character from the source file written to it.
Each non-terminal tree vertex contains two edges: left and right, which are marked with bits 0 and 1 respectively.
Each terminal vertex has a corresponding bit sequence, which is obtained by descending from the boron root to the terminal vertex and discharging the bitArchiver
In this task, you have to implement the archiver through Huffman's algorithm.
The archiver must have the following CLI:

archiver -c archive_name file1 [file2 ...] - back up fil1, file2, ... and save the result to a archive_name file.

archiver -d archive_name - unzip files from archive_name archive and put them in the current directory. File names must be preserved during backup and unzip.

archiver -h - displays help for using the program.

Algorithm
The compression algorithm is structured as follows:

The frequency of 8-bit characters in the file is calculated. In addition to the file contents, you need to consider the frequencies of characters in the file name, as well as add three service symbols FILENAME_END=256, ONE_MORE_FILE=257, ARCHIVE_END=258 with frequencies 1. The purpose of these characters will be described later. Thus, 9 bits are needed to encode the extended alphabet.
The binary encoding is built using the following procedure:

The decoding algorithm is generally inverse to the encoding algorithm and is structured as follows:

The encoding table (the correspondence between symbols and their codes) is restored from the file.
The binary boron is built from the coding table.
The binary sequences read from the input file are traced from the boron to the leaf nodes. When the next leaf node of the boron is reached, the corresponding symbol is determined and is written to the output file.

File format
Nine-bit values are written in the low-to-high format (similar to little-endian for bits). That is, the bit corresponding to 2^0 first, then 2^1, and so on to the bit corresponding to 2^8.
Within unsigned char, we count bits from youngest to oldest. For a program to be portable, you cannot rely on the order of bits in the file to match the order of bits in the binary representation of numbers in memory.
Example: given sequence unsigned char {1, 3, 7, }. You need to read two 9-bit values of a and b.
Bit level representation:
10000000 11000000 11100000
aaaaaaaa abbbbbbb bb
Hence a = 257, b = 385.
The archive file format must be:

9-bit - number of characters in SYMBOLS_COUNT alphabet

Canonical Code Recovery Data Block

SYMBOLS_COUNT values of 9 bits - alphabetical characters in order of canonical codes
List of MAX_SYMBOL_CODE_SIZE 9-bit values, i-th (for numbering from 0) item
which is the number of characters with the length of the i+1 code. MAX_SYMBOL_CODE_SIZE - Maximum length of the code in the current encoding. The canonical codes match in order the symbols from the previous point. MAX_SYMBOL_CODE_SIZE is not explicitly written to the file, because it can be restored based on existing data.

Encoded file name
Encoded FILENAME_END service symbol

Encoded file content
If there are more files in the archive, the encoded service symbol ONE_MORE_FILE and the encoding continues with p.1.
Encoded service ARCHIVE_END.

Implementation
Try to make all components of the program as versatile as possible and not tied to the specifics of a specific task.
For example, encoding and decoding algorithms should work with I/O streams, not files.
The program should correctly handle very large (many times larger RAM) files. This means that data should not be accumulated in memory when running the program.
Files with a format that does not meet the specification should not cause the program to "crash". All exceptions must be handled correctly with a user-friendly error message.
You will likely need the following components:

Wrappers over I/O streams that allow you to read and write 1- and 9-bit values.
Boron with an interface that allows you to easily bypass it.
Priority queue.

The detailed design of the program is recommended to discuss with the teacher at the seminars.

Delivery and evaluation
The project is checked by the teachers without using the automatic check system. All surrenders will pass the code review.
You will have to write the whole program from scratch, including CMakeLists.txt files.
Unlike normal homework tasks, the project must be manually packed/emptied into the repository without using the submit.py script.
To submit a project, you need to start a new branch projects/archiver (this is done once, you do not need to create a branch when you send code again):
git checkout -b projects/archiver
Use the git add and git commit commands to commit changes to a branch. Issue the git push student projects/archiver command in order to send the changes to the remote repository. Try to write meaningful explanations to the comments.
After the code has been uploaded to the remote repository, create a merge request from the projects/archiver branch in main and set your instructor as the user.
There's a lot of git stuff on the Internet, like this tutorial.
The basic implementation of the program provides a maximum score of 8 points.
You can earn more points if:

Implement a priority queue on your own without using the standard queues, algorithms, and collections that provide sorting. The implementation must be algorithmically efficient, i.e. have a I/O (logN) or less complexity, where N is the number of elements in the queue.
Test all critical components. Your seminarian will help you determine the suitability of your coverage.

Deadline
23:59 6 October 2021
