import React from 'react';
import clsx from 'clsx';
import Layout from '@theme/Layout';
import Link from '@docusaurus/Link';
import useDocusaurusContext from '@docusaurus/useDocusaurusContext';
import useBaseUrl from '@docusaurus/useBaseUrl';
import styles from './styles.module.css';

const features = [
  {
    title: 'Built on Arduino',
    imageUrl: 'https://upload.wikimedia.org/wikipedia/commons/4/42/Arduino_Uno_logo.png',
    description: (
      <>
      By leveraging Arduino's tooling, troubleshooting the hardware is never difficult.  You can start troubleshooting very quickly with a simple blink program to flash a LED.  Or you can go as complex as programming your own firmware customizations.
      </>
    ),
  },
  {
    title: 'Leverages the work of Leaders in the Maker Community',
    imageUrl: 'http://blog.tindie.com/wp-content/uploads/2014/09/adafruit-logo.png',
    description: (
      <>
        Adafruit has been making electronics easy and fun to learn for more than a decade.  The Adafruit Feather nRF52832 was the first board that made BLE available to anyone who would want to build their own BLE devices, including keyboards.  By leveraging the bootloaders and libraries Adafruit has created, we have the entire maker community helping improving our firmware.
      </>
    ),
  },
  {
    title: 'Powered by Nordic\'s nRF52832 and nRF52840 System on Chip',
    imageUrl: 'https://www.nordicsemi.com/-/media/Images/Logos/LogoTransRGBVerticalWhiteSquare.svg',
    description: (
      <>
        The BlueMicro_BLE Firmware supports the most successful BLE SoC family in the Maker Community.  They are both powerful with an 32-bit ARM® Cortex™-M4 CPU running at 64 MHz.  Both use the Nordic SoftDevices: Bluetooth protocol stacks that are pre-compiled binaries and BLE qualified when delivered, they are unaffected by the ‘develop and compile’ cycle of application development and always remain stable.
      </>
    ),
  },
];

function Feature({imageUrl, title, description}) {
  const imgUrl = useBaseUrl(imageUrl);
  return (
    <div className={clsx('col col--4', styles.feature)}>
      {imgUrl && (
        <div className="text--center">
          <img className={styles.featureImage} src={imgUrl} alt={title} />
        </div>
      )}
      <h3>{title}</h3>
      <p>{description}</p>
    </div>
  );
}

function Home() {
  const context = useDocusaurusContext();
  const {siteConfig = {}} = context;
  return (
    <Layout
      title={`Hello from ${siteConfig.title}`}
      description="Description will go into a meta tag in <head />">
      <header className={clsx('hero hero--primary', styles.heroBanner)}>
        <div className="container">
          <h1 className="hero__title">{siteConfig.title}</h1>
          <p className="hero__subtitle">{siteConfig.tagline}</p>
          <div className={styles.buttons}>
            <Link
              className={clsx(
                'button button--outline button--secondary button--lg',
                styles.getStarted,
              )}
              to={useBaseUrl('docs/')}>
              Get Started
            </Link>
          </div>
        </div>
      </header>
      <main>
        {features && features.length > 0 && (
          <section className={styles.features}>
            <div className="container">
              <div className="row">
                {features.map((props, idx) => (
                  <Feature key={idx} {...props} />
                ))}
              </div>
            </div>
          </section>
        )}
      </main>
    </Layout>
  );
}

export default Home;
