if ($args[0] -eq "clean") {
    Remove-Item output*.txt
}
elseif ($args[0] -eq "launch") {
    Write-Output("Test file");
}