# Learn how to use Vim (Vi IMproved)

## Origin

Vim is the improved version of vi (visual editor) which was originally developed by Bill Joy of UC Berkeley.

## How to use

In this section, I wrote main features of vim that I've not known..

## Command structure

The basic structure of vim command is that,
```
[command] [iterations] [target]
or
[iterations] [command] [target]
```
For example, to delete words for 4 times, type ```4dw``` or ```d4w```.

### Delete

To delete a target, put cursor into the target and type command.

The deleted target is not completely vanished but it is temporarily saved in the buffer. That means you can use the target such as using ```p``` to restore the target at the place where the cursor is located.

The one thing you should know about the buffer is that it is distinguished to the system clipboard.

**Available targets**

* w : a word with spaces.
* e : a word without spaces.
* $ : words from the current cursor position to the end of line.

Type ```dd``` to delete the whole words in the line.

### Undo and Redo

It is an essential feature in all text editors.

To undo once, type ```u```.
Vim supports multiple undos, to undo several times, type ```u``` as many times as you want.

To undo all changes in the whole line, Type ```U```.

To redo, type <kbd>Ctrl + R</kbd>.

### Put

As mentioned above, A deleted target is stored in the buffer. type ```p``` to restore it at the cursor location.

### Replace

To replace a character to another one, type ```r``` and type a new character.

### Change

Type ```ce``` to change until the end of word.

This command can also apply  ```e```, ```$```, ```w``` likes the delete command above.

### Cursor Location

Type <kbd>Ctrl + G</kbd> to show the current location in the file.

Press ```G``` to move to the end of file.

Press ```gg``` to move to the beginning of file.

Type the number of line and press G to move there.

### Search

Type ```/``` and keyword you want to search, you can find the keyword in the file.

Type ```?``` to search backward for the keyword.

Press ```n``` to find the same keyword in the same direction.

Press ```N``` to find the same one in the reversed direction.

Press <kbd>Ctrl + o</kbd> to go back to where you came from.

Press <kbd>Ctrl + i</kbd> to go forward.

### Search patterns

To search patterns such as {}, (), <>, move the cursor to the pattern you want to search and type ```%```. It's very useful when there's an omitted pattern pair.

### Substitution

To substitute the keyword, type ```s/[old keyword]/[new keyword]```.

Without any extra commands, it will be substituted to the new one only once, but add ```/g``` makes them change all old keyword occurrances in the line.

You can limit the range of substitution by adding the scope of pages explicitly in front of the command. Type ```#,#/s/[old]/[new]/g```.

To include throughout the file, Put ```%s``` in front of the command instead. Type ```%s/s/[old]/[new]/g```.

If you want to do this with confirmation, put ```c``` behind ```g```. Type ```.../gc```, then it will ask everytime.

### Run an external command

Type ```:!``` and followed by an external commands to execute the command.

Exclamation point(```!```) allows us to use external commands.

You can put arguments too.

### File

Type ```:w``` followed by file name behind a space to save to file that you named.

### Selecting texts

Press <kbd>v</kbd> and move the cursor to select text you want to grab.

If you want to save the highlighted block that you hold, Type ```w [File name]``` and press <kbd>Enter</kbd> to save the block to the file.

You can do further something with the block such as deleting by using ```d```.

### Copying text

Press ```y``` to copy (No deletion). It's convenient to use ```v``` to grab a selected block before proceeding. y means 'yank'.

y supports motions and you should explicitly have a target.

```yy``` or ```Y``` to grab the current line including the newline character at the end of line.

```y$``` to grab the current line without the newline character.

```yiw``` to grab the current word without surrounding whitespaces.

```yaw``` to grab the current word with leading or trailing whitespaces.

### Copying or cutting text into system clipboard

It is dependent on whether the vim binary is compiled with clipboard support or not.

I heard that Vim for Windows is compiled with clipboard support.

### Retrieving and merging files

To retrieve and put the contents of a file at where the cursor is located, type ```:r [Filename]```.

You can retrieve an external command output to file likewise.

For instance, If you want to get the ```ls``` command's output, type ```:r !ls [Arguments]```.

### Insert mode commands

Type ```i``` (insert) to insert before the cursor.

Type ```a``` (append) to insert after the cursor.

Type ```o``` (open) to insert a new line below the cursor and enter the insert mode at the new line.

Type ```O``` to insert a new line upper the cursor and enter the insert mode likewise.

Type ```I``` to insert at the beginning of the line.

Type ```A``` to insert at the end of the line.

Type ```ea``` to insert at the end of the word. (Think ```e``` command)

### Cursor move commands



---

Reference: vimtutor

Last Modified: Sep 6, 2022
