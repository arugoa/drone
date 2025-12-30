
import math
# input parameters

TWR = 2 # Thrust to Weight Ratio [1.5,2]

# Masses (in grams)
ChassisMass = 274
ESCMass = 26
MotorAssemblyMass = 52
ArduinoMass = 18
BatteryMass = 140


# Battery
MaxCellV = 4.2
Cells = 3
# TotalVoltage = MaxCellV * Cells # Calculate the total voltage for the battery pack
TotalVoltage = 11.1 # Conservative Estimate

# Motor Stats
MotorKV = 1100
InternalResistance = 0.192 # Ohms
PeakCurrent = 9.9 # Amps

# Calculation
# Calculate the maximum RPM of the motor
MaxNoLoadRPM = MotorKV * TotalVoltage
MotorVelocityConstant = MotorKV * 2 * math.pi / 60
MaxLoadRPM = MaxNoLoadRPM - PeakCurrent * InternalResistance / MotorVelocityConstant
MaxLoadRevsPerS = MaxLoadRPM / 60

# Thrust Calculation
CT = 0.08 # Thrust coefficient [0.08,0.12] (rough guesstimate trust aero major)
rho = 1.225 # Density [kg/m^3]
D = 9 * 2.54 / 100 # Propeller Diameter in meters

MaxThrustPerMotor = CT * rho * MaxLoadRevsPerS**2 * D ** 4
MaxTotalThrust = MaxThrustPerMotor * 4
NomninalThrust = MaxTotalThrust/TWR
MaxWeight = NomninalThrust/9.81
print(f'Theoretical Max Weight:{MaxWeight:6.2f} kg')