Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"PUNCH_LEFT"
    play-mode:"FORCE"
    clock:30
Images:
    ?ImageList(str)<"0%s.png">{197-206}:
Groups:
    @main
        ?content(int)<%s>{0-9}:
Animation:
    ?AnimationCode(str):
        "PLAY_GROUP(main, 1)"
        "CALL('IDLE_LEFT')"