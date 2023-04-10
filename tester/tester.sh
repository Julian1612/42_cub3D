#!/bin/sh

# This is a test script for the "tester" program.
echo "Working:"
FILES="./tester/maps/working/*"
for f in $FILES
do
  echo "Processing $f file..."
  ./cub3d "$f"
done

echo "\n\n"

echo "Failing:"
FILES="./tester/maps/failing/*"
for f in $FILES
do
  echo "Processing $f file..."
  ./cub3d "$f"
done