#include<iostream>

int main(){
    for(double i = -0.01; i<= 0.01; i+=0.0001){
        if(i<=0){
            std::cout << i << std::endl;
        }
    }
}