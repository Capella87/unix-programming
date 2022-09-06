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

Press ```n``` to find the same keyword again.

Press ```N``` to find the same one in the reversed direction.

Press <kbd>Ctrl + o</kbd> to go back to where you came from.

Press <kbd>Ctrl + i</kbd> to go forward.

---

Last Modified: Sep 6, 2022
