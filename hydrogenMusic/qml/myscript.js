function highLightLyric(current) {
    var sum = lyric2.startTime.length
    for (var i = 0; i < sum; i++) {
        var highLight = lyric2.startTime[i]
        if (current > highLight || current === highLight) {
            continue
        } else {
            if (i > 0)
                return i - 1
        }
    }
}

function transToString(a) {
    return String(a)
}
