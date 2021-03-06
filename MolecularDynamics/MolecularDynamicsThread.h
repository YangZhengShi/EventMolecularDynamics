#pragma once

#include <atomic>
#include <mutex>

#include "ComputationThread.h"
#include "Simulation.h"



class CMolecularDynamicsDoc;

namespace MolecularDynamics {


	class MolecularDynamicsThread :
		public ComputationThread
	{
	public:
		MolecularDynamicsThread();
		virtual ~MolecularDynamicsThread();

		CMolecularDynamicsDoc *doc;

		std::atomic_bool Terminate;
	protected:
		Simulation simulation;

		std::mutex mw;
		std::mutex mp;
		std::condition_variable cvw;
		std::condition_variable cvp;

		bool wakeup;
		bool processed;


		virtual void Calculate();
		bool PostDataToMainThread();
	public:
		void WakeUp();
		void WaitForData();
		int Init();
		double GetNextEventTime();
		std::vector<Particle> GetParticles() const;
		void WaitForWork();
		void SignalMoreData();
	};

}