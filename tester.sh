#!/bin/bash

make test

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
# arg1 > binary
# arg2 > file tested
# arg3 > return value
load_test()
{
    echo ""
    echo $1 ": "
    if [ $2 == "./my_nm" ]
    then
        $2 $3 | sort > .tmp.test 2>&1
    else
        $2 $3 > .tmp.test 2>&1
    fi
    ret=$?
    diff=`diff .tmp.test $testfile | wc -l`
    echo -n "   Return value: "
    if [ $ret -eq $4 ]
    then
        echo -e "\033[32mOK\033[00m"
        ((mark++))
    else
        echo -e "\033[31mKO\033[00m expected $4 and received $ret"
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
load_test "No such File" "./my_objdump" "azertyuiop" 84

echo "./my_objdump: .test.trunc: File truncated" > $testfile
load_test "Truncated file" "./my_objdump" ".test.trunc" 84

echo "./my_objdump: .test.not_recognize: File format not recognized" > $testfile
load_test "Format not recognize" "./my_objdump" ".test.not_recognize" 84

echo "./my_objdump: .test.trunc: File truncated" > $testfile
echo "./my_objdump: .test.trunc: File truncated" >> $testfile
load_test "Double test error" "./my_objdump" ".test.trunc .test.trunc" 84

echo "./my_objdump: tester.sh: File format not recognized" > $testfile
load_test "sh file" "./my_objdump" "tester.sh" 84

echo "./my_objdump: .test.empty: File format not recognized" > $testfile
load_test "empty file" "./my_objdump" ".test.empty" 84

echo "./my_objdump: Warning: '.test.directory' is a directory" > $testfile
load_test "directory" "./my_objdump" ".test.directory" 84

echo ""
echo "No Error"

objdump -fs my_objdump > $testfile 2>&1
load_test "my_objdump" "./my_objdump" "my_objdump" 0

objdump -fs > $testfile 2>&1
load_test "my_objdump no arg" "./my_objdump" "" 0

objdump -fs .test.binary32 > $testfile 2>&1
load_test "my_objdump 32 bit" "./my_objdump" ".test.binary32" 0

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

nm my_nm | sort > $testfile
 load_test "my_nm my_nm" "./my_nm" "my_nm" 0

nm ./.test.binary32 | sort > $testfile
load_test "my_nm 32 bit" "./my_nm" ".test.binary32" 0

gcov `find . -type f -name "*.gcno"` > .test.gcov

echo ""
echo "Final mark: $mark/$maxmark"
echo "Tester by Sahel Lucas--Saoudi"

echo ""
echo "Voulez vous avoir le % de coverage de vos tests? (Y/n)"
read r

if [ -z $r ] || ( [ $r == "Y" ] || [ $r == "y" ] )
then
    echo ""
    cat .test.gcov
fi

echo ""
echo "Voulez vousavoir un aperçu web? (Y/n)"
read r

if [ -z $r ] || ( [ $r == "Y" ] || [ $r == "y" ] )
then
    lcov --directory . --capture --output-file app.info && genhtml app.info && firefox index.html&
fi

export LANG=$lang
rm .test.not_recognize
rm -f $testfile
rm .test.empty
rm -rf .test.directory
rm .test.nm
rm .test.my_nm
rm .test.gcov
