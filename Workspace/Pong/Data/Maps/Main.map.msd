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
        path:"background.png"
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
        @Requires
            upAction:"RPaddleUp"
            downAction:"RPaddleDown"
            posX:1872
            posY:480

    @leftPaddle
        type:"Paddle"
        @Requires
            upAction:"LPaddleUp"
            downAction:"LPaddleDown"
            posX:16
            posY:480
        

    @ball
        type:"Ball"
        @Requires
            posX:928
            posY:512


Script:
    ?gameScripts(string):
        "Data/GameScripts/Pong.lua"