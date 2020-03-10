#!/bin/bash
echo "Programm for working with files (support MD5)"
echo "  You are able to:"
echo "  - Calculate a checksum with MD5 "
echo "Dev: Kravtsov Anton"
while true
do
        echo "Current directtory: $PWD"
        while true
        do
                echo "Enter path to 1st file:"
                read -r path
                if test -f "$path"
                then
                        break
                else
                        echo "No such file or  directory." >&2
                        read -p "Retry? Enter Y/N:" answer
                        if [[ "$answer" == "Y" || "$answer" == "y" ]]
                        then
                                continue
                        else
                                echo "See you soon!"
                                exit 1
                        fi
                fi
        done

        while true
        do
                echo "Enter path to 2nd file:"
                read -r path2
                if [[ -f "$path2" && -s "$path2" ]]
                then
                        echo "File is not empty. Do you want to continue?"
                        read -p "Enter Y/N:" answer
                        if [[ "$answer" == "Y" || "$answer" == "y" ]]
                        then
                                break
                        else
                                echo "See you soon!"
                                exit 2
                        fi
                else
                        if test -f "$path2"
                        then
                                 break
                        else
                                 echo "No such file or  directory." >&2
                                 read -p "Retry? Enter Y/N:" answer
                                 if [[ "$answer" == "Y" || "$answer" == "y" ]]
                                 then
                                         continue
                                 else
                                         echo "See you soon!"
                                         exit 3
                                 fi
                        fi
                        
                fi
        done
        md5sum $path > $path2
        read -p "MD5 checksum complete.Exit? Enter Y/N:" answer
        if [[ "$answer" == "N" || "$answer" == "n" ]]
                        then
                                continue
                        else
                                echo "See you soon!"
                                exit 4
        fi

done