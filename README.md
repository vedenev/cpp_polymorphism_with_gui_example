# cpp_polymorphism_with_gui_example
C++ polymorphism with GUI example
![shcreenshot image](/pictures/screenshot1.png)  
  
It is example of polymorphism in C++ with GUI. See polymorph_learning_try3.cpp.  
It has interface view.h that is common interface for gui widget objects button and checkbox.  
check_mouse function is fully virtual. Also it has virtual distructor.  
It has container of polymorphic objects:  
```
view** views_all;
```
```
for (int view_count = 0; view_count < N_VIEWS; view_count++)
	{
		views_all[view_count]->check_mouse(image, x, y, event);
	}
```
Function pointers was used for callbacks.  
OpenCV was used for graphics.  
It was made in visual studio comunity 2019.  
I had opencv compiled before. I added msvcp120d.dll, msvcr120d.dll, msvcp120.dll, msvcr120.dll files.  

