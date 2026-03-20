
if [ -e "test" ]; then
    rm "test"
else 
    exit
fi

g++ ./main.cpp -o test
./test
