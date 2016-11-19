Define Flag (Map);
Define Flag (Lock);

Meta:
    Level:"Main"
    SizeX:1920
    SizeY:1080
    StartX:0
    StartY:0

LevelSprites:
    @g2V27QPw
        type:"PONG_Background"
        posX:0
        posY:0
        rotation:0
        scale:1.000000
        layer:1
        z-depth:1


Collisions:

LevelObjects:
    @rightPaddle
        type:"Paddle"
        posX:1872
        posY:480

    @leftPaddle
        type:"Paddle"
        posX:16
        posY:480

    @ball
        type:"Ball"
        posX:928
        posY:512


Script:
    ?gameScripts(string):
        "Data/GameScripts/Pong.lua"