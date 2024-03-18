
<h1 align="center">
  <br>
  C++ Daily Task Manager
  <br>
</h1>

<h4 align="center">A desktop application that allows tasks to be added, removed, and set to completed.</h4>

<p align="center">
  <a href="#key-features">Key Features</a> ▪︎
  <a href="#installation">Installation</a> ▪︎ 
  <a href="#libraries-used">Libraries Used</a>
</p>

<div align="center">
  <video src="https://github.com/MrT-Stephens/CSharp-Digital-Vending-Machine/assets/92452307/df413820-4f9f-4656-86ef-1eeede66972e"/>
</div>
    
## Key Features

* Tasks can be added with a task name, description, start time, and end time.
* Remove tasks by clicking the remove button for the task.
* You can set a task to be completed by clicking the complete checkbox.
* Persistent storage for the tasks, which is encrypted for safekeeping. So, all tasks will be saved to an XML file at the end of the application lifetime and inputted from the XML file at the beginning of the application lifetime.
* When writing the tasks, the data gets Base64 encoded and Vigenere encrypted, and upon reading the data gets Vigenere decrypted and Base64 and decoded.

## Installation

To clone and run this application, you'll need [Git](https://git-scm.com). You will then need to run the commands shown below:

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
