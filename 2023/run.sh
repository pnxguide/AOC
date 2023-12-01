echo "Compling and running day${1}/solution.cpp..."
g++ -std=c++20 -o solution "day${1}/solution.cpp";
time ./solution;
rm ./solution;