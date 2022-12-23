echo "Compling and running day${1}/solution.cc..."
g++ -std=c++11 -o solution "day${1}/solution.cc";
time ./solution;
rm ./solution;