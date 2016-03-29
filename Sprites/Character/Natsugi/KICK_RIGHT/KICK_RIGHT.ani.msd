Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"KICK_RIGHT"
    play-mode:"ONETIME"
    clock:70
Images:
    ?ImageList(str)<"0%s.png">{207-216}:
Groups:
    @main
        ?content(int)<%s>{0-9}:
Animation:
    ?AnimationCode(str):
        "PLAY_GROUP(main, 1)"
        "CALL('IDLE_RIGHT')"