Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"SIDEFLIP_LEFT"
    clock:0
Images:
    ?ImageList(str)<"0%s.png">{153-162}:
Groups:
    @start
        clock:50
        ?content(int)<%s>{0-7}:
    @main
        clock:70
        ?content(int)<%s>{8-9}:
Animation:
    ?AnimationCode(str):
        "PLAY_GROUP(start, 1)"
        "PLAY_GROUP(main, -1)"