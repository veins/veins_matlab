if ~matlab.engine.isEngineShared
    fprintf('Init: sharing engine.\n');
    matlab.engine.shareEngine('veins');
else
    fprintf('Init: engine already shared.\n');
end