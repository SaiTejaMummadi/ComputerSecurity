Execution instructions:

$cd source
$make

If the make file is not working:
Please run:
g++ MerkleGen.cpp -o MerkleGen
g++ VerifyTx.cpp -o VerifyTx 


To test the Merkle Tree
$./MerkleGen 3 Tx6

$./VerifyTx root.txt branch.txt Tx6


