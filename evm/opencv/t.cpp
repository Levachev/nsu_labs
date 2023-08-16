libusb_device_descriptor desc; // дескриптор устройства
 libusb_config_descriptor *config; // дескриптор конфигурации объекта
 const libusb_interface *inter;
 const libusb_interface_descriptor *interdesc;
 const libusb_endpoint_descriptor *epdesc;
 int r = libusb_get_string_descriptor_ascii(dev, &desc);
 if (r < 0){
 fprintf(stderr,
 "Ошибка: дескриптор устройства не получен, код: %d.\n",r);
 return;
 }
 //libusb_open()
 // получить конфигурацию устройства
 libusb_get_config_descriptor(dev, 0, &config);
 printf("%.2d %.2d %.4d %.4d %.3d | | | | | |\n",
 (int)desc.bNumConfigurations,
 (int)desc.bDeviceClass,
 desc.idVendor,
 desc.idProduct,
 (int)config->bNumInterfaces
 );
 for(int i=0; i<(int)config->bNumInterfaces; i++){
 inter = &config->interface[i];
 printf("| | | | | "
 "%.2d %.2d | | | |\n",
 inter->num_altsetting,
 (int)desc.bDeviceClass
 );
 for(int j=0; j<inter->num_altsetting; j++) {
 interdesc = &inter->altsetting[j];
 printf("| | | | | | | "
 "%.2d %.2d | |\n",
 (int)interdesc->bInterfaceNumber,
 (int)interdesc->bNumEndpoints
 );
 for(int k=0; k<(int)interdesc->bNumEndpoints; k++) {
 epdesc = &interdesc->endpoint[k];
 printf(
 "| | | | | | | | | "
 "%.2d %.9d\n",
 (int)epdesc->bDescriptorType,
 (int)(int)epdesc->bEndpointAddress
 );
 }
 }
 }