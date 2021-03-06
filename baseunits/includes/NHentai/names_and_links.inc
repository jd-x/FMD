  function NHentaiNamesAndLinks: Byte;
  var
    i: Integer;
  begin
    Result := INFORMATION_NOT_FOUND;
    if not GetPage(TObject(Source), WebsiteRoots[NHENTAI_ID, 1] +
      '/?page=' + IntToStr(StrToInt(URL) + 1), 0) then
    begin
      Result := NET_PROBLEM;
      Source.Free;
      Exit;
    end;
    parse.Clear;
    Parser := THTMLParser.Create(PChar(Source.Text));
    Parser.OnFoundTag := OnTag;
    Parser.OnFoundText := OnText;
    Parser.Exec;
    Parser.Free;
    if parse.Count = 0 then
    begin
      Source.Free;
      Exit;
    end;
    for i := 0 to parse.Count - 1 do
    begin
      if (Pos('/g/', parse[i]) > 0) and (Pos('<a', parse[i]) > 0) then
      begin
        Result := NO_ERROR;
        names.Add(Trim(HTMLEntitiesFilter(StringFilter(Trim(parse[i + 1])))));
        links.Add(StringReplace(GetVal(parse[i], 'href'), WebsiteRoots[NHENTAI_ID, 1], '', [rfIgnoreCase]));
      end;
    end;
    Source.Free;
  end;
