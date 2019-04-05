mkdir data
if [$? != 0]; then
    echo "data folder present"
else
    echo "created a new data folder"
fi