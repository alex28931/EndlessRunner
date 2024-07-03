// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

void UMyHUD::SetCurrentTime(float Time)
{
	CurrentTimeText->SetText(FText::AsNumber(Time));
}

void UMyHUD::SetRecordTime(float Time)
{
	RecordTimeText->SetText(FText::AsNumber(Time));
}
