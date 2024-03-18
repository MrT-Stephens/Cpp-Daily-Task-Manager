
<h1 align="center">
  <br>
  C++ Daily Task Manager
  <br>
</h1>

<h4 align="center">A desktop application that allows tasks to be added, removed, and set to completed.</h4>

<p align="center">
  <a href="#key-features">Key Features</a> ▪︎
  <a href="#installation">Installation</a> ▪︎ 
  <a href="#libraries-used">Libraries Used</a> ▪︎ 
  <a href="#license">License</a>
</p>

<div align="center">
  <img src="https://github.com/MrT-Stephens/Cpp-Daily-Task-Manager/assets/92452307/67a7cd32-bdf5-4987-99ed-51754645e078" alt="drawing"/>
</div>
    
## Key Features

* Tasks can be added with a task name, description, start time, and end time.
* Remove tasks by clicking the remove button for the task.
* You can set a task to be completed by clicking the complete checkbox.
* Persistent storage for the tasks, which is encrypted for safekeeping. So, all tasks will be saved to an XML file at the end of the application lifetime and inputted from the XML file at the beginning of the application lifetime.
* When writing the tasks, the data gets Base64 encoded and Vigenere encrypted, and upon reading the data gets Vigenere decrypted and Base64 and decoded.

## Installation

To clone and run this application, you'll need [Git](https://git-scm.com). You will then need to run the commands shown below. You must use a recursive clone when cloning the repository, as the GUI library is added as a submodule.

```bash
# Clone this repository
$ git clone --recursive https://github.com/MrT-Stephens/CSharp-Digital-Vending-Machine.git

# Go into the repository
$ cd Cpp-Drawing-Application
```
> **Note**
> Once cloned, open the `CPP-Daily-Task-Manager` folder in your specified code editor and compile it, and the application should just work.

## Libraries Used

* [Elements](https://github.com/cycfi/elements): Used for creating the cross-platform GUI application.
* [Easy Encryption](https://github.com/philipperemy/easy-encryption): Used for encrypting/decrypting the data from files.

## License

MIT License

Copyright (c) 2024 Thomas Stephens

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
