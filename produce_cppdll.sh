cd ./cpp_evaluate
g++ -fopenmp -o ../py_train_model/bee_dll/libpymcts.so -shared -fPIC main.cpp eval.cpp search.cpp 
#g++ -o ../py_train_model/bee_dll/libpymcts.so -shared -fPIC main.cpp eval.cpp search.cpp 