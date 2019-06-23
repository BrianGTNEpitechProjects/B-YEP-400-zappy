#!/bin/bash

PLAYER_PER_TEAM=10
NAME="team"
PORT=4242
MACHINE="localhost"

echo "Enter the number of players per team (default: 10):"
read buf

if [ ! -z $buf ]
then
    PLAYER_PER_TEAM=$buf
fi

echo "Enter team name (default: team):"
read buf

if [ ! -z $buf ]
then
    NAME=$buf
fi

echo "Enter port (default: 4242):"
read buf

if [ ! -z $buf ]
then
    PORT=$buf
fi

echo "Enter machine name (default: localhost):"
read buf

if [ ! -z $buf ]
then
    MACHINE=$buf
fi

re='^[0-9]+$'

if ! [[ $PLAYER_PER_TEAM =~ $re ]]
then
    echo $PLAYER_PER_TEAM
    exit 84
fi


for ((i = 0; i < PLAYER_PER_TEAM; i++))
do
    ./zappy_ai -p $PORT -n $NAME -h $MACHINE &
done
