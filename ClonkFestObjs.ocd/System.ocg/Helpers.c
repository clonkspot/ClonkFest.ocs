global func PlrArray2String(array players)
{
	var s, n;
	if (!players || !(n=GetLength(players)))
		s = "$MsgNoone$";
	else
	{
		s = "";
		for (var i=0; i<n; ++i)
		{
			var fs;
			if (i==n-1)
				fs = "";
			else if (i==n-2)
				fs = " $MsgAnd$ ";
			else
				fs = ", ";
			s = Format("%s%s%s", s, GetTaggedPlayerName(players[i]), fs);
		}
	}
	return s;
}

// Shuffle array in place
global func ShuffleArray(array arr)
{
	var n = GetLength(arr);
	for (var i = 0; i < n; ++i)
	{
		var j = Random(n);
		var v = arr[j];
		arr[j] = arr[i];
		arr[i] = v;
	}
	return arr;
}