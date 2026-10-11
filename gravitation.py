import math
import random
import time

N = 1000
STEPS = 200
G = 6.67430e-11
DT = 1000.0


class Particle:
    def __init__(self):
        self.x = random.uniform(-1e11, 1e11)
        self.y = random.uniform(-1e11, 1e11)
        self.z = random.uniform(-1e11, 1e11)

        self.vx = random.uniform(-1e3, 1e3)
        self.vy = random.uniform(-1e3, 1e3)
        self.vz = random.uniform(-1e3, 1e3)

        self.mass = random.uniform(1e20, 1e25)


def main():

    random.seed(42)

    # Initialize particles
    particles = [Particle() for _ in range(N)]

    start = time.perf_counter()

    for step in range(STEPS):

        # Calculate gravitational acceleration
        for i in range(N):

            ax = 0.0
            ay = 0.0
            az = 0.0

            pi = particles[i]

            for j in range(N):

                if i == j:
                    continue

                pj = particles[j]

                dx = pj.x - pi.x
                dy = pj.y - pi.y
                dz = pj.z - pi.z

                distance_squared = (
                    dx * dx +
                    dy * dy +
                    dz * dz
                )

                # Softening prevents singularities
                distance = math.sqrt(
                    distance_squared + 1e16
                )

                factor = (
                    G * pj.mass /
                    (distance * distance * distance)
                )

                ax += factor * dx
                ay += factor * dy
                az += factor * dz

            # Update velocity
            pi.vx += ax * DT
            pi.vy += ay * DT
            pi.vz += az * DT

        # Update position
        for i in range(N):

            p = particles[i]

            p.x += p.vx * DT
            p.y += p.vy * DT
            p.z += p.vz * DT

        if step % 100 == 0:
            print(f"Step {step} / {STEPS}")

    elapsed = time.perf_counter() - start

    print()
    print("Simulation finished.")
    print(f"Time: {elapsed:.3f} seconds")

    # Checksum
    checksum = 0.0

    for p in particles:
        checksum += p.x
        checksum += p.y
        checksum += p.z

    print(f"Checksum: {checksum:.10e}")


if __name__ == "__main__":
    main()