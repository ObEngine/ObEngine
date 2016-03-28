Define Flag (Anim);
Define Flag (Lock);

Meta:
    name:"SIT_RIGHT"
    play-mode:"ONETIME"
    clock:70
Images:
    ?ImageList(str)<"000%s.png">{6-9}:
        "0010.png"
        "0011.png"
Groups:
    @main
        ?content(int)<%s>{0-5}:
Animation:
    ?AnimationCode(str):
        "PLAY_GROUP(main, 1)"
        "CALL('SITTED_RIGHT')"