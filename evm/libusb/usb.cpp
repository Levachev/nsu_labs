#include <iostream>
//#include <libusb.h>
#include <libusb-1.0/libusb.h>
#include <stdio.h>
using namespace std;


void printdev(libusb_device *dev);


int main(){

 libusb_device **devs; // указатель на указатель на устройство,
 // используется для получения списка устройств

 libusb_context *ctx = NULL; // контекст сессии libusb

 int r; // для возвращаемых значений

 ssize_t cnt; // число найденных USB-устройств

 ssize_t i; // индексная переменная цикла перебора всех устройств

 // инициализировать библиотеку libusb, открыть сессию работы с libusb
 r = libusb_init(&ctx);

 if(r < 0){
 fprintf(stderr, "Ошибка: инициализация не выполнена, код: %d.\n", r);
 return 1;
 }

 // задать уровень подробности отладочных сообщений
 libusb_set_debug(ctx, 3);

 // получить список всех найденных USB- устройств
 cnt = libusb_get_device_list(ctx, &devs);

 if(cnt < 0){
 fprintf(stderr,"Ошибка: список USB устройств не получен.\n", r);
 return 1;
 }

 for(i = 0; i < cnt; i++) { // цикл перебора всех устройств
 printdev(devs[i]); // печать параметров устройства
 }

 // освободить память, выделенную функцией получения списка устройств
 libusb_free_device_list(devs, 1);

 libusb_exit(ctx); // завершить работу с библиотекой libusb,
 // закрыть сессию работы с libusb

 return 0;
}

void printdev(libusb_device *dev){

libusb_device_descriptor desc;
//libusb_config_descriptor *config;
//const libusb_interface *inter;
//const libusb_interface_descriptor *interdesc;
//const libusb_endpoint_descriptor *epdesc;

int r = libusb_get_device_descriptor(dev, &desc); 

if (r < 0){
 fprintf(stderr, "Ошибка: дескриптор устройства не получен, код: %d.\n",r);
 return;
 }

 //libusb_get_config_descriptor(dev, 0, &config);

 printf("bDeviceClass -  %.2d\n", (int)desc.bDeviceClass);
 
 /*for(int i=0; i<(int)config->bNumInterfaces; i++){

 inter = &config->interface[i];
 printf("2 bDeviceClass -  %.2d\n", (int)desc.bDeviceClass);

 }*/


 libusb_device_handle* handle=nullptr;
 libusb_open(dev, &handle);
 if(handle){
    unsigned char s[200];

    /*if(desc.bDeviceClass){
        libusb_get_string_descriptor_ascii(handle, desc.bDeviceClass, s, sizeof(s));
        printf("bDeviceClass - %s \n", s);
    }*/

    if(desc.iManufacturer){
        libusb_get_string_descriptor_ascii(handle, desc.iManufacturer, s, sizeof(s));
        printf("iManufacturer - %s \n", s);
    }
    if(desc.iProduct){
        libusb_get_string_descriptor_ascii(handle, desc.iProduct, s, sizeof(s));
        printf("iProduct - %s \n", s);
    }
    if(desc.iSerialNumber){
        libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, s, sizeof(s));
        printf("iSerialNumber - %s \n", s);
    }
    std::cout<<std::endl;
 }

 //libusb_free_config_descriptor(config);

 libusb_close(handle);
}
 
