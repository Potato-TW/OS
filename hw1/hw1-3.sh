#!/bin/bash

flag=0
# Read parent pid, child pid
while [ "$#" -gt 0 ]; do
  case "$1" in
    --parent)
      parent="$2"
      shift 2
      ;;
    --child)
      child="$2"
      shift 2
      ;;
    --path)
      # echo "eeee"
      flag=1
      shift 1
      ;;
    *)
      echo "Unknown parameter passed: $1"
      exit 1
      ;;
  esac
done

# Check if parent or child is empty
if [ -z "$parent" ] || [ -z "$child" ]; then
  echo "Usage: $0 --parent PARENT_PID --child CHILD_PID [--path]"
  exit 1
fi

########
# TODO #

realParent=$child
arr=($child)

while [ $parent -ne $realParent ] && [ $parent -lt $realParent ] 
do
  child=$realParent
  realParent=`$(echo ps -o ppid= $child)`
  arr+=($realParent)
done

if [ $parent -eq $realParent ]; then
  echo "Yes"
  
  if [ $flag -eq 1 ]; then
    # echo "flag"
    for ((i=${#arr[@]}-1;i>0;i--)); do
      echo -n "${arr[$i]} -> "
    done
    echo -n "${arr[0]}"
  # else
  #     echo "no flag"
  fi

else
  echo "No"
fi
########

# The code below is only for demonstration purposes, please remove it before submitting.
# echo "parent pid: $parent, child pid: $child"
