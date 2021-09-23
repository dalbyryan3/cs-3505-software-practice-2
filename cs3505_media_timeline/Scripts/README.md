1. for each script that needs to be run they must be enabled as executeable
2. go to the directory where the scripts are located

3. run the following commands; these will make the shell scripts executeable
	chmod +x stockscript.sh
	chmod +x twitchscript.sh
	chmod +x newsscript.sh
	chmod +x aqiscript.sh
	chmod +x twitterscript.sh
	chmod +x spotifyscript.sh
	
4. set up the cron job; 
	1. crontab -e
	2. if you haven't selected an editor to edit your 		   crontab with, select it, nano will do fine for 		   our purposes. 
	3. scroll down to the bottom of your cron tab
	4. cron runs in the following format:
	\* \* \* \* \* command output
	5. the 2nd star is the only one we are concerning 		   ourselves with here, it selects the hour of the 		   day the crontab runs on, 
	6. leave the output blank, we aren't using that
	7. command should look something like this /home/Directory/file/path/script.sh
	8. save your tab and close it and it should work
