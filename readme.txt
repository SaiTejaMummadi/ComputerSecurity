Execution instructions:

$cd source
$make

$cp virus seed
$printf "\xde\xad\xbe\xef" >> seed
$cat host1 >> seed	

$./seed ./host1
$./host1 ./host2
$./host2 ./host3

I was using a MacBook so I didn't have use the chmod command. If using chmod is the case:
$chmod ugo-x ./host1
$chmod ugo-x ./host2
$chmod ugo-x ./host3

$./seed ./host1
$chmod ugo+x host1
$./host1 ./host2
$chmod ugo+x host2
$./host2 ./host3

Mutation:
For each infection:
An additional number is added to the end of the file before the 0xdeadbeef. This number helps the virus mutate itself and the hash outputs are different for each host file.

