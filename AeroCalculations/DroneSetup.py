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
BatteryNum = 1
MaxCellV = 4.2
Cells = 3
# TotalVoltage = MaxCellV * Cells # Calculate the total voltage for the battery pack
TotalVoltage = 11.1 # Conservative Estimate
BatteryCapacity = 2700 # in mAh
BatteryCapacity = BatteryCapacity/1000

# Motor Stats
MotorKV = 1100
InternalResistance = 0.192 # Ohms
PeakCurrent = 9.9 # Amps

# Calculation
# Calculate the maximum RPM of the motor
MaxLoadRPM = MotorKV * (TotalVoltage- (PeakCurrent * InternalResistance))
MaxLoadRevsPerS = MaxLoadRPM / 60


# Thrust Calculation
CT = 0.11 # Thrust coefficient [0.08,0.12] (rough guesstimate trust aero major)
rho = 1.225 # Density [kg/m^3]
D = 9 * 2.54 / 100 # Propeller Diameter in meters

MaxThrustPerMotor = CT * rho * MaxLoadRevsPerS**2 * D ** 4
MaxTotalThrust = MaxThrustPerMotor * 4
NomninalThrust = MaxTotalThrust/TWR
MaxMass = NomninalThrust/9.81
print(f'Theoretical Max Mass:{MaxMass:6.2f} kg')
CurrentMass = (ChassisMass + (ESCMass + MotorAssemblyMass) * 4 + ArduinoMass + BatteryMass * BatteryNum )/1e3
MassMargin = MaxMass - CurrentMass
print("Current Mass:", CurrentMass, "kg")
print("Mass Margin:", MassMargin, "kg")

# Flight Time and Power Calculations
CurrentWeight = CurrentMass * 9.81
ThurstHover = CurrentWeight
nHover = math.sqrt(ThurstHover/(CT * rho * D**4))

CP = 0.06 #see UIUC database, just a roughguesstimate
P = CP * rho * nHover ** 3 * D ** 5 #idealized power draw
AmpDraw = P/TotalVoltage + 1 # Plus one amp to account for other electronics
tflight = BatteryCapacity * 0.8 * 60 / AmpDraw
print("Theoretical max flight time:", tflight, "min")