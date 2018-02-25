#!/bin/bash

make re
lang=$LANG
testfile=".test.assert"
export LANG="en_EN.UTF-8"
echo -e "File format not recognize" > .test.not_recognize
cp my_objdump a.out
touch .test.empty
mkdir .test.directory
mark=0
maxmark=0

# arg0 > TestName
# arg1 > file tested
# arg2 > return value
load_test()
{
    echo ""
    echo $1 ": "
    ./my_objdump $2 > .tmp.test 2>&1
    ret=$?
    diff=`diff .tmp.test $testfile | wc -l`
    echo -n "   Return value: "
    if [ $ret -eq $3 ]
    then
        echo -e "\033[32mOK\033[00m"
        ((mark++))
    else
        echo -e "\033[31mKO\033[00m expected $3 and received $ret"
    fi

    echo -n "   Output:"
    if [ $diff -eq 0 ]
    then
	    echo -e "\033[32mOK\033[00m"
	    ((mark++))
    else
	    echo -e "\033[31mKO\033[00m : \n"
	    diff .tmp.test $testfile
    fi
    rm .tmp.test

    ((maxmark++))
    ((maxmark++))
}


echo "Error Tests"
echo "./my_objdump: 'azertyuiop': No such file" > $testfile
load_test "No such File" "azertyuiop" 84

echo "./my_objdump: .test.trunc: File truncated" > $testfile
load_test "Truncated file" ".test.trunc" 84

echo "./my_objdump: .test.not_recognize: File format not recognized" > $testfile
load_test "Format not recognize" ".test.not_recognize" 84

echo "./my_objdump: .test.trunc: File truncated" > $testfile
echo "./my_objdump: .test.trunc: File truncated" >> $testfile
load_test "Double test error" ".test.trunc .test.trunc" 84

echo "./my_objdump: tester.sh: File format not recognized" > $testfile
load_test "sh file" "tester.sh" 84

echo "./my_objdump: .test.empty: File format not recognized" > $testfile
load_test "empty file" ".test.empty" 84

echo "./my_objdump: Warning: '.test.directory' is a directory" > $testfile
load_test "directory" ".test.directory" 84

echo ""
echo "No Error"

objdump -fs my_objdump > $testfile 2>&1
load_test "my_objdump" "my_objdump" 0

objdump -fs > $testfile 2>&1
load_test "my_objdump no arg" "" 0

objdump -fs .test.binary32 > $testfile 2>&1
load_test "my_objdump 32 bit" ".test.binary32" 0

echo ""
echo "Test nm all lib of docker"

echo "cd work && nm /usr/bin/* 2> /dev/null | sort > .test.nm && ./my_nm /usr/bin/* 2> /dev/null | sort > .test.my_nm && diff .test.nm .test.my_nm" > $testfile
docker run -it -v `pwd`:/work epitechcontent/epitest-docker bash /work/$testfile

if [ $? -eq 0 ]
then
	echo -e "\033[32mOK\033[00m"
    ((mark++))
else
    echo -e "\033[31mKO\033[00m"
fi
((maxmark++))

echo ""
echo "Final mark: $mark/$maxmark"
echo "Tester by Sahel Lucas--Saoudi"

export LANG=$lang
rm .test.not_recognize
rm -f $testfile
rm .test.empty
rm -rf .test.directory
rm .test.nm
rm .test.my_nm