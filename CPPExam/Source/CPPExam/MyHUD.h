// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class CPPEXAM_API UMyHUD : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void SetCurrentTime(float Time);
	void SetRecordTime(float Time);

protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentTimeText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RecordTimeText;

};
