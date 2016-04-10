#Trainer Card Modification     
   
###How to use: (Be sure to have devkitarm & GNU make installed)     
   
######1. Make these byte changes   
8A028: 9A    
8A144: 98    
3CD930: 45    
3CD932: 57    
3CD934: 5C    
######2. Create an empty folder called build and change the insert offset in linker.lsc.    
######3. Open the cmd prompt (or cygwin) and type in make.      
######4. Insert main.bin at the offset assigned in step2.     
######5. Change the pointers at the following offsets:    
3A7360: pointer to offset of inserting main.bin + 0x71.   
3CD914: pointer to offset of inserting main.bin + 0x6F1.    
Example: I insert main.bin at 0x800000 so I write 71 00 80 08 and F1 06 80 08.   
   
###Credits: knizz, Coranac