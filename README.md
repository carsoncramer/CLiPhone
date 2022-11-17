# CLiPhone
If you're like me you enjoy doing everything from the the terminal. 
Now, you can initiate phone calls. 


## Setup
Pull code and in the directory run
```
make
```
To compile.


Next run 
```
sh setup.sh
```
This will move the call command into your usr/local/bin folder so you can call it like any other shell command!


After that, in the terminal type 
```
call {insert number here}
```
To initiate the phone call!

Soon I am planning on using the Levenshtein distance on your contacts to guess what person you are talking about and call that number. ie. "call john d" will initiate a call to John Doe if he is in your contacts. Stay tuned!
