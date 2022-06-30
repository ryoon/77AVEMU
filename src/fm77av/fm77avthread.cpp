#include "fm77avthread.h"
#include "fm77avcommand.h"
#include "outside_world.h"
#include <chrono>
#include <iostream>



FM77AVThread::FM77AVThread() : renderingThread(new FM77AVRenderingThread)
{
}
FM77AVThread::~FM77AVThread()
{
}
void FM77AVThread::SetRunMode(unsigned int runMode)
{
	this->runMode=runMode;
}
void FM77AVThread::VMStart(FM77AV *fm77avPtr,class Outside_World *outside_world,FM77AVUIThread *uiThread)
{
	this->fm77avPtr=fm77avPtr;
	renderingThread->imageNeedsFlip=outside_world->ImageNeedsFlip();
	// In Tsugaru,
	//   Set outside_world pointers to devices
	outside_world->Start();
}
void FM77AVThread::VMMainLoop(FM77AV *fm77avPtr,class Outside_World *outside_world,FM77AVUIThread *uiThread)
{
	// Just in case, if there is a remains of the rendering from the previous run, discard it.
	renderingThread->DiscardRunningRenderingTask();

	PrintStatus(*fm77avPtr);	

	FM77AVRender render;
	bool terminate=false;
	for(;true!=terminate;)
	{
		auto realTime0=std::chrono::high_resolution_clock::now();
		auto fm77avTime0=fm77avPtr->state.fm77avTime;

		int runModeCopy=0;

		runModeCopy=runMode;

		bool clockTicking=false;  // Will be made true if VM is running.

		fm77avPtr->var.justLoadedState=false;

		switch(runMode)
		{
		case RUNMODE_PAUSE:
			renderingThread->WaitIdle();
			// fm77avPtr->ForceRender(render,*outside_world);
			outside_world->DevicePolling(*fm77avPtr);
			//if(true==outside_world->PauseKeyPressed())
			//{
			//	runMode=RUNMODE_RUN;
			//	fm77avPtr->debugger.stop=false;
			//}
			break;
		case RUNMODE_RUN:
			clockTicking=true;
			{
				auto nextTimeSync=fm77avPtr->state.fm77avTime+NANOSECONDS_PER_TIME_SYNC;
				while(fm77avPtr->state.fm77avTime<nextTimeSync && true!=fm77avPtr->CheckAbort())
				{
					fm77avPtr->RunOneInstruction();
					fm77avPtr->ProcessInterrupts();
					// fm77avPtr->RunFastDevicePolling();
					// fm77avPtr->RunScheduledTasks();

					//auto payBack=std::min<long long int>(TIME_DEFICIT_PAYBACK_PER_INSTRUCTION,timeDeficit);
					//fm77avPtr->state.fm77avTime+=payBack;
					//timeDeficit-=payBack;

					bool shouldBreak=false;
					for(int cpuId=0; cpuId<2; ++cpuId)
					{
						auto &cpu=fm77avPtr->CPU(cpuId);
						auto &mem=fm77avPtr->MemAccess(cpuId);
						if(true==cpu.debugger.enabled)
						{
							if(true==cpu.debugger.stop)
							{
								// if(fm77avPtr->cpu.state.CS().value==fm77avPtr->var.powerOffAt.SEG &&
								//    fm77avPtr->cpu.state.EIP==fm77avPtr->var.powerOffAt.OFFSET)
								// {
								// 	std::cout << "Break at the power-off point." << std::endl;
								// 	std::cout << "Normal termination of a unit testing." << std::endl;
								// 	fm77avPtr->var.powerOff=true;
								// 	break;
								// }
								//if(true!=fm77avPtr->debugger.lastBreakPointInfo.ShouldBreak())
								//{
								//	if(0!=(fm77avPtr->debugger.lastBreakPointInfo.flags&i486Debugger::BRKPNT_FLAG_MONITOR_ONLY) ||
								//	   0==(fm77avPtr->debugger.lastBreakPointInfo.flags&i486Debugger::BRKPNT_FLAG_SILENT_UNTIL_BREAK))
								//	{
								//		std::cout << "Passed " << fm77avPtr->debugger.lastBreakPointInfo.passedCount << " times." << std::endl;
								//		PrintStatus(*fm77avPtr);
								//	}
								//	fm77avPtr->debugger.ClearStopFlag();
								//	this->SetRunMode(RUNMODE_RUN);
								//}
								//else
								//{
								// std::cout << "Passed " << fm77avPtr->debugger.lastBreakPointInfo.passedCount << " times." << std::endl;
								PrintCPUState(*fm77avPtr,cpu,mem,cpuId);
								std::cout << ">";
								runMode=RUNMODE_PAUSE;
								shouldBreak=true;
							}
							else if(true==cpu.debugger.PollMonitorPoint())
							{
								PrintCPUState(*fm77avPtr,cpu,mem,cpuId);
							}
						}
					}
					if(true==shouldBreak)
					{
						break;
					}
				}
			}
			// fm77avPtr->ProcessSound(outside_world);

			renderingThread->CheckRenderingTimer(*fm77avPtr,render);
			renderingThread->CheckImageReady(*fm77avPtr,*outside_world);

			// outside_world->ProcessAppSpecific(*fm77avPtr);
			if(fm77avPtr->state.nextDevicePollingTime<fm77avPtr->state.fm77avTime)
			{
				outside_world->DevicePolling(*fm77avPtr);
				fm77avPtr->state.nextDevicePollingTime=fm77avPtr->state.fm77avTime+FM77AV::DEVICE_POLLING_INTERVAL;
			}
			//fm77avPtr->eventLog.Interval(*fm77avPtr);
			if(true==fm77avPtr->CheckAbort() || outside_world->PauseKeyPressed())
			{
				PrintStatus(*fm77avPtr,false,false); // In case of Abort, disregard mute flags.
				std::cout << ">";
				runMode=RUNMODE_PAUSE;
			}
			break;
		case RUNMODE_ONE_INSTRUCTION:
			if(true!=fm77avPtr->CheckAbort())
			{
				fm77avPtr->RunOneInstruction();
				fm77avPtr->ProcessInterrupts();
				//fm77avPtr->RunFastDevicePolling();
				//fm77avPtr->RunScheduledTasks();
			}
			PrintStatus(*fm77avPtr);
			std::cout << ">";
			runMode=RUNMODE_PAUSE;
			break;
		case RUNMODE_EXIT:
			terminate=true;
			break;
		default:
			terminate=true;
			std::cout << "Undefined VM RunMode!" << std::endl;
			break;
		}
		//if(fm77avPtr->state.nextSecondInfm77avTime<=fm77avPtr->state.fm77avTime)
		//{
		//	fm77avPtr->state.nextSecondInfm77avTime+=PER_SECOND;
		//	fm77avPtr->fdc.SaveModifiedDiskImages();
		//	fm77avPtr->physMem.state.memCard.SaveRawImageIfModified();
		//}

		//if(RUNMODE_PAUSE==runModeCopy)
		//{
		//	fm77avPtr->fdc.SaveModifiedDiskImages();
		//	std::this_thread::sleep_for(std::chrono::milliseconds(10));
		//	if(true==returnOnPause)
		//	{
		//		break;
		//	}
		//}

		uiThread->uiLock.lock();
		while(true!=outside_world->commandQueue.empty())
		{
			auto cmdStr=outside_world->commandQueue.front();
			std::cout << cmdStr << std::endl;
			outside_world->commandQueue.pop();
			FM77AVCommandInterpreter interpreter;
			auto cmd=interpreter.Interpret(cmdStr);
			interpreter.Execute(*this,*fm77avPtr,outside_world,cmd);
		}
		uiThread->ExecCommandQueue(*this,*fm77avPtr,outside_world);
		uiThread->uiLock.unlock();
		if(true==fm77avPtr->var.justLoadedState)
		{
			renderingThread->DiscardRunningRenderingTask();
		}
		else if(true==clockTicking)
		{
			AdjustRealTime(fm77avPtr,fm77avPtr->state.fm77avTime-fm77avTime0,realTime0,outside_world);
		}
	}

	// Rendering thread may be working on local fm77avRender.
	// WaitIdle to make sure the rendering thread is done with rendering before leaving this function.
	renderingThread->DiscardRunningRenderingTask();
}
void FM77AVThread::VMEnd(FM77AV *fm77avPtr,class Outside_World *outside_world,FM77AVUIThread *uiThread)
{
	uiThread->uiLock.lock();
	uiThread->vmTerminated=true;
	uiThread->uiLock.unlock();

	std::cout << "Ending FM77AV Thread." << std::endl;
	// fm77avPtr->fdc.SaveModifiedDiskImages();

	// Save dictionary RAM?

	outside_world->Stop();

	if(true==fm77avPtr->var.forceQuitOnPowerOff)
	{
		exit(0);
	}
}

void FM77AVThread::AdjustRealTime(FM77AV *fm77avPtr,long long int cpuTimePassed,std::chrono::time_point<std::chrono::high_resolution_clock> time0,class Outside_World *outside_world)
{
}
void FM77AVThread::PrintStatus(FM77AV &fm77av) const
{
	PrintStatus(fm77av,output.main.mute,output.sub.mute);
}
void FM77AVThread::PrintStatus(FM77AV &fm77av,bool muteMain,bool muteSub) const
{
	if(true==fm77av.CheckAbort())
	{
		std::cout << "Abort" << std::endl;
		std::cout << fm77av.vmAbortDeviceName << std::endl;
		std::cout << fm77av.vmAbortReason << std::endl;
	}

	if(true!=muteMain && true!=muteSub)
	{
		if(0<fm77av.state.timeBalance)
		{
			std::cout << "Main CPU is ahead by " << fm77av.state.timeBalance << " nanoseconds." << std::endl;
		}
		else if(fm77av.state.timeBalance<0)
		{
			std::cout << "Sub CPU is ahead by " << -fm77av.state.timeBalance << " nanoseconds." << std::endl;
		}
		PrintCPUState(fm77av,fm77av.mainCPU,fm77av.mainMemAcc,CPU_MAIN);
		PrintCPUState(fm77av,fm77av.subCPU,fm77av.subMemAcc,CPU_SUB);
	}
	else if(true!=muteMain)
	{
		if(output.main.lastPC!=fm77av.mainCPU.state.PC)
		{
			PrintCPUState(fm77av,fm77av.mainCPU,fm77av.mainMemAcc,CPU_MAIN);
			output.main.lastPC=fm77av.mainCPU.state.PC;
		}
	}
	else if(true!=muteSub)
	{
		if(output.sub.lastPC!=fm77av.subCPU.state.PC)
		{
			PrintCPUState(fm77av,fm77av.subCPU,fm77av.subMemAcc,CPU_SUB);
			output.sub.lastPC=fm77av.subCPU.state.PC;
		}
	}}
void FM77AVThread::PrintCPUState(FM77AV &fm77av,MC6809 &cpu,MemoryAccess &mem,unsigned int mainOrSub) const
{
	std::cout << '[' << CPUToStr(mainOrSub) << " CPU]";
	if(CPU_SUB==mainOrSub)
	{
		if(true==fm77av.state.subSysBusy)
		{
			std::cout << " BUSY ";
		}
		else
		{
			std::cout << " READY";
		}
		if(true==fm77av.state.subSysHalt)
		{
			std::cout << " HALT";
		}
		else
		{
			std::cout << " RUN ";
		}
	}
	std::cout << std::endl;
	for(auto str : cpu.GetStatusText())
	{
		std::cout << str << std::endl;
	}
	std::cout << cpu.WholeDisassembly(mem,cpu.state.PC) << std::endl;
}
