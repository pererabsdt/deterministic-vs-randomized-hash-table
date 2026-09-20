import csv
import matplotlib.pyplot as plt
import os

def generate_plots():
    # Create plots directory
    os.makedirs('plots', exist_ok=True)
    
    # Data structures
    results = []
    
    try:
        with open('benchmark_results.csv', 'r') as f:
            reader = csv.DictReader(f)
            for row in reader:
                results.append({
                    'TestName': row['TestName'],
                    'TableSize': int(row['TableSize']),
                    'DataSize': int(row['DataSize']),
                    'InsertTimeMs': float(row['InsertTimeMs']),
                    'LookupTimeMs': float(row['LookupTimeMs']),
                    'DeleteTimeMs': float(row['DeleteTimeMs']),
                    'MaxChainLength': int(row['MaxChainLength'])
                })
    except Exception as e:
        print(f"Error loading CSV: {e}")
        return

    # -------------------------------------------------------------
    # 1. Bar Plot: Max Chain Lengths for Benign vs Adversarial vs Avalanche
    # -------------------------------------------------------------
    static_tests = [r for r in results if 'Degradation' not in r['TestName']]
    
    test_names = [r['TestName'] for r in static_tests]
    max_chains = [r['MaxChainLength'] for r in static_tests]
    
    plt.figure(figsize=(12, 6))
    plt.bar(test_names, max_chains, color=['#440154', '#414487', '#2a788e', '#22a884', '#7ad151', '#fde725'])
    plt.title('Maximum Chain Length (Collisions) by Hash Table Version & Data Type', fontsize=14)
    plt.ylabel('Max Chain Length (Log Scale)')
    plt.xlabel('Test Variant')
    plt.yscale('log')
    plt.xticks(rotation=45, ha='right')
    plt.tight_layout()
    plt.savefig('plots/max_chain_lengths.png', dpi=300)
    plt.close()

    # -------------------------------------------------------------
    # Degradation Line Plots
    # -------------------------------------------------------------
    deg_tests = [r for r in results if 'Degradation' in r['TestName']]
    
    if not deg_tests:
        print("No degradation data found to plot.")
        return
        
    # Group by TestName
    deg_grouped = {}
    for r in deg_tests:
        name = r['TestName']
        if name not in deg_grouped:
            deg_grouped[name] = {'DataSize': [], 'LookupTimeMs': [], 'DeleteTimeMs': [], 'InsertTimeMs': []}
        deg_grouped[name]['DataSize'].append(r['DataSize'])
        deg_grouped[name]['LookupTimeMs'].append(r['LookupTimeMs'])
        deg_grouped[name]['DeleteTimeMs'].append(r['DeleteTimeMs'])
        deg_grouped[name]['InsertTimeMs'].append(r['InsertTimeMs'])

    markers = ['o', 's', '^', 'D']
    colors = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728']
    
    # 2. Line Plot: Lookup Time Degradation
    plt.figure(figsize=(10, 6))
    for i, (name, data) in enumerate(deg_grouped.items()):
        plt.plot(data['DataSize'], data['LookupTimeMs'], label=name, marker=markers[i%len(markers)], color=colors[i%len(colors)], linewidth=2)
    
    plt.title('Lookup Time Degradation vs Table Load', fontsize=14)
    plt.ylabel('Time for 1000 Lookups (ms)')
    plt.xlabel('Data Size (N)')
    plt.legend()
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.tight_layout()
    plt.savefig('plots/lookup_time_degradation.png', dpi=300)
    plt.close()

    # 3. Line Plot: Deletion Time Degradation
    plt.figure(figsize=(10, 6))
    for i, (name, data) in enumerate(deg_grouped.items()):
        plt.plot(data['DataSize'], data['DeleteTimeMs'], label=name, marker=markers[i%len(markers)], color=colors[i%len(colors)], linewidth=2)
    
    plt.title('Deletion Time Degradation vs Table Load', fontsize=14)
    plt.ylabel('Time for 1000 Deletions (ms)')
    plt.xlabel('Data Size (N)')
    plt.legend()
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.tight_layout()
    plt.savefig('plots/delete_time_degradation.png', dpi=300)
    plt.close()
    
    # 4. Line Plot: Insertion Time Degradation
    plt.figure(figsize=(10, 6))
    for i, (name, data) in enumerate(deg_grouped.items()):
        plt.plot(data['DataSize'], data['InsertTimeMs'], label=name, marker=markers[i%len(markers)], color=colors[i%len(colors)], linewidth=2)
    
    plt.title('Insertion Time Degradation vs Table Load', fontsize=14)
    plt.ylabel('Total Insertion Time (ms)')
    plt.xlabel('Data Size (N)')
    plt.legend()
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.tight_layout()
    plt.savefig('plots/insert_time_degradation.png', dpi=300)
    plt.close()

    print("All plots generated and saved in the 'plots/' directory!")

if __name__ == "__main__":
    generate_plots()
