all: main gen con
main:     ; g++ main.cpp -o main -pthread
gen:      ; g++ generator.cpp -o generator
con:      ; g++ convertor.cpp -o convertor
run:      ; ./main 
valgrind: ; valgrind --leak-check=full ./main
clean:    ; rm -rf main generator convertor;