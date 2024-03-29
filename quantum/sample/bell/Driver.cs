﻿using System;

using Microsoft.Quantum.Simulation.Core;
using Microsoft.Quantum.Simulation.Simulators;

namespace Quantum.Bell
{
    class Driver
    {
        static void Main(string[] args)
        {
            using (var qsim = new QuantumSimulator())
            {
                Result[] initials = new Result[] {Result.Zero, Result.One};
                foreach(Result initial in initials)
                {
                    var (numZeros, numOnes) = BellTest.Run(qsim, 1000, initial).Result;
                    System.Console.WriteLine($"Init:{initial,-4} 0s={numZeros,-4} 1s={numOnes,-4}");
                }
            }

            System.Console.WriteLine("Press any key to continue...");
            Console.ReadKey();
        }
    }
}